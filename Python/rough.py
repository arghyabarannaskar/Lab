try:
    a = int(input('Enter an integer: '))
    b = int(input('Enter an integer: '))
    c = a/b
    print('c = ', c)
except ZeroDivisionError as zde:
    print('Denominator is 0')
    print(zde.args)
    print(zde)
except ValueError:
    print('Unable to convert string to int')
except: 
    print('Some unknow error') 