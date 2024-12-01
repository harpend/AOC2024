// package main

// import (
// 	"bufio"
// 	"log"
// 	"os"
// 	"strconv"
// 	"strings"
// )

// func main() {
// 	file, err := os.Open("input.txt")
// 	if err != nil {
// 		log.Fatalf("couldn't open")
// 	}

// 	scanner := bufio.NewScanner(file)
// 	scanner.Split(bufio.ScanLines)
// 	var line1 []int
// 	var line2 []int
// 	for scanner.Scan() {
// 		text := strings.Split(scanner.Text(), "   ")
// 		i1, err := strconv.Atoi(text[0])
// 		if err != nil {
// 			log.Fatalf("couldn't convert %s", text[0])
// 		}
// 		i2, err := strconv.Atoi(text[1])
// 		if err != nil {
// 			log.Fatalf("couldn't convert %s", text[1])
// 		}
// 		line1 = append(line1, i1)
// 		line2 = append(line2, i2)
// 	}

// 	line1 = quickSort(line1, 0, len(line1)-1)
// 	line2 = quickSort(line2, 0, len(line2)-1)
// 	diff := computeDiff(line1, line2)
// 	log.Println(diff)
// }

// func swap(a *int, b *int) {
// 	t := *a
// 	*a = *b
// 	*b = t
// }

// func quickSort(arr []int, low int, high int) []int {
// 	if low < high {
// 		pi := partition(arr, low, high)
// 		quickSort(arr, low, pi-1)
// 		quickSort(arr, pi+1, high)
// 	}

// 	return arr
// }

// func partition(arr []int, low int, high int) int {
// 	pivot := arr[high]
// 	i := low - 1
// 	for j := low; j <= high; j++ {
// 		if arr[j] < pivot {
// 			i++
// 			swap(&arr[i], &arr[j])
// 		}
// 	}

// 	swap(&arr[i+1], &arr[high])
// 	return i + 1
// }

// func computeDiff(arr1 []int, arr2 []int) int {
// 	if len(arr1) != len(arr2) {
// 		log.Fatalf("not same length")
// 	}

// 	var total int
// 	total = 0

// 	for i := 0; i < len(arr1); i++ {
// 		diff := (arr1[i] - arr2[i])
// 		if diff < 0 {
// 			total = total - (arr1[i] - arr2[i])
// 		} else {
// 			total = total + (arr1[i] - arr2[i])
// 		}
// 	}

// 	return int(total)
// }
