package main

import (
	"fmt"
	"github.com/garyburd/redigo/redis"
)

const N = 1000000

func main() {
	c, err := redis.Dial("tcp", ":6379")
	errorHandler(err)
	defer c.Close()

	fmt.Println("Connected!")

	for i := 0; i < N; i++ {
		c.Send("SET", "foo", "bar")
	}
	c.Flush()
	fmt.Println("Done")
}

func errorHandler(err error) {
	if err != nil {
		panic(fmt.Sprintln("error:", err))
	}
}
