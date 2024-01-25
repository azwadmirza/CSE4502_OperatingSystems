read -r str
consonants=${str//[aeiouAEIOU]}
vowels=${str//[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]}
echo "Vowels: $vowels"
echo "Consonants: $consonants"

