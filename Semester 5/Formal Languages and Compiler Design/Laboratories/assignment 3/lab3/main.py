class FiniteAutomaton:
    def __init__(self):
        self.states = set()
        self.alphabet = set()
        self.initial_state = None
        self.final_states = set()
        self.transitions = {}

    def read_from_file(self, filename):
        with open(filename, "r") as f:
            lines = [line.strip() for line in f if line.strip() and not line.startswith("#")]

        reading_transitions = False

        for line in lines:
            if line.startswith("states"):
                inside = line.split("{")[1].split("}")[0]
                self.states = {s.strip() for s in inside.split(",") if s.strip()}

            elif line.startswith("alphabet"):
                inside = line.split("{")[1].split("}")[0]
                self.alphabet = {s.strip() for s in inside.split(",") if s.strip()}

            elif line.startswith("initial_state"):
                self.initial_state = line.split("=")[1].strip()

            elif line.startswith("final_states"):
                inside = line.split("{")[1].split("}")[0]
                self.final_states = {s.strip() for s in inside.split(",") if s.strip()}

            elif line.startswith("transitions"):
                reading_transitions = True
                continue

            elif reading_transitions:
                if "}" in line:
                    reading_transitions = False
                    continue
                line = line.replace(";", "").strip()
                if not line:
                    continue
                left, right = line.split("->")
                left = left.strip("() ").split(",")
                source = left[0].strip()
                symbol = left[1].strip()
                dest = right.strip()
                self.transitions[(source, symbol)] = dest

    def display(self):
        print("States:", self.states)
        print("Alphabet:", self.alphabet)
        print("Initial State:", self.initial_state)
        print("Final States:", self.final_states)
        print("\nTransitions:")
        for (state, symbol), next_state in self.transitions.items():
            print(f"  δ({state}, {symbol}) -> {next_state}")
        print("\n")

    def check_sequence(self, sequence):
        current = self.initial_state
        for char in sequence:
            symbol = self.classify_symbol(char)
            if (current, symbol) in self.transitions:
                current = self.transitions[(current, symbol)]
            else:
                return False
        return current in self.final_states

    def classify_symbol(self, char):
        if char.isalpha():
            return "LETTER"
        elif char.isdigit():
            return "DIGIT"
        elif char == "_":
            return "_"
        elif char == '"' or char == "'":
            return "QUOTE"
        elif char == "+":
            return "PLUS"
        elif char == "-":
            return "MINUS"
        elif char == "*":
            return "MULT"
        elif char == "/":
            return "DIV"
        elif char == "=":
            return "EQUAL"
        elif char == "(":
            return "LPAREN"
        elif char == ")":
            return "RPAREN"
        elif char == "{":
            return "LBRACE"
        elif char == "}":
            return "RBRACE"
        elif char == "[":
            return "LBRACKET"
        elif char == "]":
            return "RBRACKET"
        elif char == ";":
            return "SEMICOLON"
        elif char == ",":
            return "COMMA"
        elif char == ".":
            return "DOT"
        elif char == ":":
            return "COLON"
        else:
            return None


if __name__ == "__main__":
    files = ["FA_identifiers.txt", "FA_integer.txt", "FA_operator.txt", "FA_string.txt", "FA_separator.txt"]

    print("Automaton files:")
    for i in range(len(files)):
        print(f"  {i+1}. {files[i]}")

    choice = input("\nEnter number: ")
    num = int(choice)

    filename = files[num - 1]

    fa = FiniteAutomaton()
    fa.read_from_file(filename)
    fa.display()

    if "identifier" in filename:
        tests = ["abc_1", "var_99", "_temp", "myVar123", "1abc", "9start", "hello"]
    elif "integer" in filename:
        tests = ["123", "0", "456789", "12a", "abc"]
    elif "operator" in filename:
        tests = ["+", "-", "*", "/", "=", "++", "abc"]
    elif "string" in filename:
        tests = ['"hello"', '"abc123"', '"test_var"', '"unclosed', 'hello"', "abc"]
    elif "separator" in filename:
        tests = ["(", ")", "{", "}", "[", "]", ";", ",", ".", ":", "ab", "()"]
    else:
        tests = ["test1", "test2"]

    print("Testing sequences:")
    for t in tests:
        result = fa.check_sequence(t)
        if result:
            print(f"  {t:15} -> ACCEPTED")
        else:
            print(f"  {t:15} -> REJECTED")