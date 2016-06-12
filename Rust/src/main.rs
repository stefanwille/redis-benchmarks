extern crate redis;
use redis::PipelineCommands;

fn main() {
    let client = redis::Client::open("redis://127.0.0.1/").unwrap();
    let con = client.get_connection().unwrap();

    let mut pipeline = redis::pipe();
    for _ in 1..1_000_000 {
        pipeline.set("foo", "bar").ignore();
    }
    pipeline.execute(&con);
}
