import re

# Define custom exceptions
class UserException(Exception):
    pass

class UsernameNotUniqueException(UserException):
    pass

class InvalidAgeException(UserException):
    pass

class UserUnderAgeException(UserException):
    pass

class InvalidEmailException(UserException):
    pass

# Function to validate email
def is_valid_email(email):
    return bool(re.match(r"[^@]+@[^@]+\.[^@]+", email))

# Main function to add users
def add_users(user_data):
    user_directory = {}
    for username, email, age in user_data:
        try:
            # Check if username is unique
            if username in user_directory:
                raise UsernameNotUniqueException(f"Username '{username}' is not unique.")
            
            # Check if age is a positive integer
            if not isinstance(age, int) or age <= 0:
                raise InvalidAgeException(f"Age '{age}' is not a positive integer.")
            
            # Check if user is at least 16 years old
            if age < 16:
                raise UserUnderAgeException(f"User '{username}' is under 16 years old.")
            
            # Check if email is valid
            if not is_valid_email(email):
                raise InvalidEmailException(f"Email '{email}' is not valid.")
            
            # Add user to the directory
            user_directory[username] = email

        except UsernameNotUniqueException as e:
            print(e)
        except InvalidAgeException as e:
            print(e)
        except UserUnderAgeException as e:
            print(e)
        except InvalidEmailException as e:
            print(e)
        except UserException as e:
            print(f"An error occurred: {e}")

    return user_directory

# Example user data
user_data = [
    ("john_doe", "john@example.com", 25),
    ("jane_doe", "jane@example.com", 15),
    ("john_doe", "john2@example.com", 30),
    ("sam_smith", "sam@example", 22),
    ("lucy_liu", "lucy@example.com", -5),
    ("tim_lee", "tim@example.com", 16)
]

# Run the function with example data
user_directory = add_users(user_data)
print("User Directory:", user_directory)
