#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <ranges>
#include <string_view>
#include <uv.h>



inline std::string getHttpHeader(std::uint16_t status_code, std::string status, std::vector<std::pair<std::string, std::string>> headers)
{
    std::string response;
    response += "HTTP/1.1 " + std::to_string(status_code) + " " + status + "\r\n";
    for (const auto& each_pair : headers)
    {
        response += each_pair.first + ": " + each_pair.second + "\r\n";
    }
    return response;
}


inline std::vector<std::string_view> split(std::string_view str, std::string sep, int max_sep = -1) {
    std::vector<std::string_view> result;
    size_t start{ str.find_first_not_of(sep) };
    size_t end{};
    while (start != std::string_view::npos) {
        if (result.size() >= max_sep)
            break;
        end = str.find_first_of(sep, start + 1);
        if (end == std::string_view::npos)
            end = str.length();
        result.push_back(str.substr(start, end - start));
        start = str.find_first_not_of(sep, end + 1);
    }
    return result;
}



class HttpRequest
{
public:
    std::string method;
    std::string url;
    std::string version;
    std::vector<std::pair<std::string, std::string>> params;
public:
    static HttpRequest parse(std::string request_text)
    {
        HttpRequest result;
        auto lines = split(request_text, "\r\n");
        if (lines.size() == 0)
        {
            fprintf(stderr, "Parse error\n");
            return result;
        }
        auto first_line = lines[0];
        auto first_line_values = split(first_line, " ");
        if (first_line_values.size() != 3)
        {
            fprintf(stderr, "Parse error\n");
            return result;
        }
        result.method = first_line_values[0];
        result.url = first_line_values[1];
        result.version = first_line_values[2];

        for (int i = 1; i < lines.size(); ++i)
        {
            auto key_pair = split(lines[i], ": ", 2);
            if (key_pair.size() != 2)
            {
                fprintf(stderr, "Parse error\n");
                return result;
            }
            result.params.push_back(std::make_pair(std::string(key_pair[0]), std::string(key_pair[1])));
        }

        return result;
    }
};


class HttpServer
{
private:
    uv_loop_t* loop;
    uv_tcp_t server;
    struct sockaddr_in addr;

    inline static std::map<int, std::string> status_code{
        {200, "OK"},
        {404, "Not Found"},
        {501, "Not Implemented"}
    };
public:
    HttpServer(const char* ip, std::uint16_t port)
    {
        loop = uv_default_loop();
        uv_tcp_init(loop, &server);
        uv_ip4_addr(ip, port, &addr);
        uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    }
    int listen()
    {
        int r = uv_listen((uv_stream_t*)&server, 128, on_new_connection);
        if (r) {
            fprintf(stderr, "Listen error %s\n", uv_strerror(r));
            return 1;
        }
    }

    static void free_handle(uv_handle_t* handle) {
        delete handle;
    }

    static void on_new_connection(uv_stream_t* server, int status) {
        uv_loop_t* loop = uv_default_loop();
        if (status < 0) {
            fprintf(stderr, "New connection error %s\n", uv_strerror(status));
            return;
        }

        uv_tcp_t* client = new uv_tcp_t;
        uv_tcp_init(loop, client);
        if (uv_accept(server, (uv_stream_t*)client) == 0) {
            uv_read_start((uv_stream_t*)client, alloc_buffer, read_cb);
        }
        else
        {
            uv_close((uv_handle_t*)client, free_handle);
        }
    }

    static void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
        buf->base = new char[suggested_size];
        buf->len = suggested_size;
    }

    static void write_cb(uv_write_t* req, int status) {
        if (status) {
            fprintf(stderr, "Write error %s\n", uv_strerror(status));
        }
        delete[] req->data;
        delete req;
    }

    static void read_cb(uv_stream_t* client, ssize_t nread, const uv_buf_t* buf) {
        if (nread < 0) {
            if (nread != UV_EOF) {
                fprintf(stderr, "Read error %s\n", uv_err_name(nread));
                uv_close((uv_handle_t*)client, free_handle);
            }
        }
        else if (nread > 0) {
            uv_write_t* req = new uv_write_t;
            std::string request_text{ buf->base, static_cast<std::size_t>(nread) };
            HttpRequest request_obj = HttpRequest::parse(request_text);
            std::string body = "<html>"\
                "<body>"\
                "<h1>"\
                + request_obj.url +
                "</h1>"\
                "</body>"\
                "</html>";
            std::string header = getHttpHeader(200, status_code[200],
                {
                    {"Content-Type", "text/html"},
                    {"Content-Length", std::to_string(body.length())}
                }
            );
            std::string response = header + "\r\n" + body;
            char* ret = new char[response.length()];
            memcpy(ret, response.c_str(), response.length());
            // uv_buf_t wrbuf = uv_buf_init(buf->base, nread);
            uv_buf_t wrbuf = uv_buf_init(ret, response.length());
            req->data = ret;
            uv_write(req, client, &wrbuf, 1, write_cb);
        }

        if (buf->base) {
            delete buf->base;
        }
    }

};

int main() {
    uv_loop_t* loop = uv_default_loop();
    HttpServer server("0.0.0.0", 7000);
    server.listen();
    return uv_run(loop, UV_RUN_DEFAULT);
}