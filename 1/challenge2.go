package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

// create a map to count from the sencond list and in the first list iterate
// through and multiply based on this
func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		log.Fatalf("couldn't open")
	}

	scanner := bufio.NewScanner(file)
	scanner.Split(bufio.ScanLines)
	var line1 []int
	var line2 []int
	m := make(map[int]int)
	for scanner.Scan() {
		text := strings.Split(scanner.Text(), "   ")
		i1, err := strconv.Atoi(text[0])
		if err != nil {
			log.Fatalf("couldn't convert %s", text[0])
		}
		i2, err := strconv.Atoi(text[1])
		if err != nil {
			log.Fatalf("couldn't convert %s", text[1])
		}

		m[i2]++
		line1 = append(line1, i1)
		line2 = append(line2, i2)
	}

	similarity := compSim(line1, m)
	log.Println(similarity)
}

func compSim(arr []int, m map[int]int) int {
	total := 0
	for i := 0; i < len(arr); i++ {
		total = total + (arr[i] * m[arr[i]])
	}

	return total
}
