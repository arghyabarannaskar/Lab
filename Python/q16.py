from collections import Counter

class CustomString:
    def __init__(self, text):
        self.text = text

    def __len__(self):
        words = self.text.split()
        word_counts = Counter(words)
        if len(word_counts) == len(words):
            return len(self.text)
        else:
            repetitive_length = sum(len(word) for word in words if word_counts[word] > 1)
            return repetitive_length

    def most_common(self, n=1):
        words = self.text.split()
        word_counts = Counter(words)
        return word_counts.most_common(n)

custom_string = CustomString("this is a test this is only a test")

print("Length:", len(custom_string))
print("Most common words:", custom_string.most_common(3))
