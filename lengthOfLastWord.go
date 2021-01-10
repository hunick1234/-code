func lengthOfLastWord(s string) int {
	length := 0
	s = strings.TrimSpace(s) // 將字串頭尾空白鍵去除 " sa s "=>"sa s"
	for i := len(s) - 1; i >= 0; i-- {
		if s[i] == ' ' {
			break
		} else {
			length++
		}
	}
	return length
}
