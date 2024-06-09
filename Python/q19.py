from collections import OrderedDict

stock_prices = OrderedDict([
    ('AAPL', 1500),
    ('GOOGL', 2500),
    ('MSFT', 1200),
    ('AMZN', 3000),
    ('FB', 1800)
])


min_price = min(stock_prices.values())
max_price = max(stock_prices.values())

sorted_stock_prices = OrderedDict(sorted(stock_prices.items(), key=lambda x: x[1]))


second_stock_prices = {
    'AAPL': 800,
    'GOOGL': 2500,
    'TSLA': 1200,
    'MSFT': 1200,
    'AMZN': 3000
}


only_in_first_dict = {key: value for key, value in stock_prices.items() if key not in second_stock_prices}

prices_do_not_match = {key: (stock_prices[key], second_stock_prices[key]) for key in stock_prices if key in second_stock_prices and stock_prices[key] != second_stock_prices[key]}

duplicate_items_removed = OrderedDict({key: value for key, value in stock_prices.items() if value % 500 != 0})


item_with_price_800 = {key: value for key, value in stock_prices.items() if value == 800}
item_with_price_800_second_dict = {key: value for key, value in second_stock_prices.items() if value == 800}

print("Minimum Price:", min_price)
print("Maximum Price:", max_price)
print("Sorted Stock Prices:", sorted_stock_prices)
print("Items Only in First Dictionary:", only_in_first_dict)
print("Items Whose Prices Do Not Match:", prices_do_not_match)
print("First Dictionary with Duplicate Items Removed (Multiple of 500):", duplicate_items_removed)
print("Item with Price 800 in First Dictionary:", item_with_price_800)
print("Item with Price 800 in Second Dictionary:", item_with_price_800_second_dict)
