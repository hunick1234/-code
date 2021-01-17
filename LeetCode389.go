func findTheDifference(s string, t string) byte {
	gg := [26]int{}
	x := len(s)
	for i := 0; i < x; i++ {
		gg[s[i]-97]++ //a in 0[array]
		gg[t[i]-97]--
	}
	gg[t[x]-97]--
	for i := 0; i < 26; i++ {
		if gg[i] != 0 {
			return byte(i + 97)
		}
	}
	return 0
}
