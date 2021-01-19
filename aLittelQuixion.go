func main() {

	i := []int{1, 3, 5}

	fmt.Println(numOfSubarrays(i))

}
func numOfSubarrays(arr []int) int {
	x := len(arr)
	var count, i int
	ag := func(i int) {
		//var a = i
		//s := 0
		for ; i < x; i++ {
			s := 0
			for a := i; a <= i; a++ {
				s += arr[a]
				fmt.Println(s)

			}

			if s%2 != 0 {
				count++
			}

		}
	}
	for i < x {
		ag(i)
		i++
	}

	return count
}
