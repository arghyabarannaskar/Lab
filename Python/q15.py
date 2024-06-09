class BankAccount:
    def __init__(self, account_number, initial_balance=0, pin=None):
        self.account_number = account_number
        self.balance = initial_balance
        self.pin = pin

    def deposit(self, amount):
        if amount > 0:
            self.balance += amount
            return True
        return False

    def withdraw(self, amount):
        if 0 < amount <= self.balance:
            self.balance -= amount
            return True
        return False

    def get_balance(self):
        return self.balance

    def change_pin(self, old_pin, new_pin):
        if self.pin is None or self.pin == old_pin:
            self.pin = new_pin
            return True
        return False

class SavingsAccount(BankAccount):
    def __init__(self, account_number, initial_balance=0, pin=None, interest_rate=0.01):
        super().__init__(account_number, initial_balance, pin)
        self.interest_rate = interest_rate

    def apply_interest(self):
        self.balance += self.balance * self.interest_rate

class FeeSavingsAccount(SavingsAccount):
    def __init__(self, account_number, initial_balance=0, pin=None, interest_rate=0.01, withdrawal_fee=5):
        super().__init__(account_number, initial_balance, pin, interest_rate)
        self.withdrawal_fee = withdrawal_fee

    def withdraw(self, amount):
        total_amount = amount + self.withdrawal_fee
        if 0 < total_amount <= self.balance:
            self.balance -= total_amount
            return True
        return False

account = BankAccount("12345678", initial_balance=1000, pin="1234")
print("Initial Balance:", account.get_balance())
account.deposit(500)
print("Balance after deposit:", account.get_balance())
account.withdraw(200)
print("Balance after withdrawal:", account.get_balance())
account.change_pin("1234", "5678")

savings_account = SavingsAccount("87654321", initial_balance=1000, pin="4321", interest_rate=0.05)
print("Savings Account Initial Balance:", savings_account.get_balance())
savings_account.apply_interest()
print("Balance after applying interest:", savings_account.get_balance())

fee_savings_account = FeeSavingsAccount("11223344", initial_balance=1000, pin="1111", interest_rate=0.05, withdrawal_fee=10)
print("Fee Savings Account Initial Balance:", fee_savings_account.get_balance())
fee_savings_account.apply_interest()
print("Balance after applying interest:", fee_savings_account.get_balance())
fee_savings_account.withdraw(100)
print("Balance after withdrawal with fee:", fee_savings_account.get_balance())
