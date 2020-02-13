namespace cpp prismarine

struct ValueItem {
    1: i64 id,
    2: string content,
}

struct ReturnItem {
    1: i32 status,
    2: ValueItem value,
}

service CallService {
    oneway void call(1:list<ValueItem> params),
    oneway void ret(1:ReturnItem value),
}