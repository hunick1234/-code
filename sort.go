func main() {
	math := [...]int{1, 5, 45, 10, 71, 20, 3, 70, 8, 44}
	sort(math[:])
	fmt.Println(math)
}
func sort(math []int) {
	for i := len(math); i > 0; i-- {
		var count int
		
		for a := 0; a < i-1; a++ {
			if math[a] < math[a+1] {
				count++
				math[a], math[a+1] = math[a+1], math[a]
			}
		}
		if count == 0 {
			break
		}

	}
}
