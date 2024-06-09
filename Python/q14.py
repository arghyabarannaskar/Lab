class TextAnalyzer:
    def __init__(self, text):
        self.text = text
        self.words = self._extract_words()

    def _extract_words(self):
        import string
        translator = str.maketrans(string.punctuation, ' ' * len(string.punctuation))
        cleaned_text = self.text.translate(translator).lower()
        words = cleaned_text.split()
        return words

    def find_palindromes(self):
        palindromes = [word for word in self.words if word == word[::-1]]
        return set(palindromes)

    def find_unique_words(self):
        unique_words = set(self.words)
        return unique_words

text = "Madam, in Eden, I'm Adam. Eve saw Bob racecar and Hannah at noon. Did Eve see Bob?"

analyzer = TextAnalyzer(text)

palindromes = analyzer.find_palindromes()
unique_words = analyzer.find_unique_words()

print("Palindromes:", palindromes)
print("Unique words:", unique_words)
