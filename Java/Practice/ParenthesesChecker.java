import java.util.Stack;

public class ParenthesesChecker {
    public static boolean isBalanced(String str) {
        Stack<Character> stack = new Stack<>();

        for (char c : str.toCharArray()) {
            if (c == '(' || c == '[' || c == '{') {
                stack.push(c);
            } else if (c == ')' || c == ']' || c == '}') {
                if (stack.isEmpty()) {
                    return false; // Unmatched closing bracket
                }
                char top = stack.pop();
                if ((c == ')' && top != '(') || (c == ']' && top != '[') || (c == '}' && top != '{')) {
                    return false; // Mismatched opening and closing brackets
                }
            }
        }

        return stack.isEmpty(); // Check if there are any unmatched opening brackets left
    }

    public static void main(String[] args) {
        String str = "{[()]}";
        if (isBalanced(str)) {
            System.out.println("The string \"" + str + "\" is balanced.");
        } else {
            System.out.println("The string \"" + str + "\" is not balanced.");
        }
    }
}
