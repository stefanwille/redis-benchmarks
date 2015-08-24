extern crate redis;

const N : usize = 1000000;

fn main() {
    run().unwrap();
}

fn run() -> redis::RedisResult<()> {
    let client = try!(redis::Client::open("redis://127.0.0.1/"));
    let con = try!(client.get_connection());

    let mut pipe = redis::pipe();
    for _ in 0..N {
        pipe.cmd("SET").arg("foo").arg("bar").ignore();
    }

    pipe.query(&con)
}
