def flatten_dict(nested_dict, parent_key='', separator='_'):
    flattened_dict = {}
    for key, value in nested_dict.items():
        new_key = f"{parent_key}{separator}{key}" if parent_key else key
        if isinstance(value, dict):
            flattened_dict.update(flatten_dict(value, new_key, separator))
        elif isinstance(value, list):
            for i, item in enumerate(value):
                flattened_dict[f"{new_key}{separator}{i}"] = item
        else:
            flattened_dict[new_key] = value
    return flattened_dict

nested = {
    'fullname': 'Alessandra',
    'age': 41,
    'phone-numbers': ['+447421234567', '+447423456789'],
    'residence': {
        'address': {
            'first-line': 'Alexandra Rd',
            'second-line': '',
        },
        'zip': 'N8 OPP',
    }
}

flattened = flatten_dict(nested)
print(flattened)
