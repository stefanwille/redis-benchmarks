# rustc 1.4.0-nightly (63ba780fd 2015-08-23)

## Install

Install Rust, either through your package manager or using a package from [the official download page](https://www.rust-lang.org/install.html).

## Build

```
cargo build --release
```

## Run

```
$ time ./target/release/redis-rs-performance
```

## My Results

```
$ time ./target/release/redis-rs-performance
real	0m4.124s
user	0m1.767s
sys	0m1.497s
```

=> 242,500 cps
