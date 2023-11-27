import sys

def invert_string_by_group_of_4(input_string):
    while len(input_string) % 4 != 0:
        input_string = '/' + input_string

    hex_string = input_string.encode().hex()

    hex_groups = [hex_string[i:i+8] for i in range(0, len(hex_string), 8)]

    inverted_groups = []
    for group in hex_groups:
        pairs = [group[i:i+2] for i in range(0, len(group), 2)]
        pairs.reverse()
        inverted_group = ''.join(pairs)
        inverted_groups.append(f"push 0x{inverted_group}")

    inverted_groups.reverse()

    return '\n'.join(inverted_groups)

if len(sys.argv) > 1:
    test_string = sys.argv[1]
    inverted_string = invert_string_by_group_of_4(test_string)
    print(inverted_string)
else:
    print("Please provide a string as an argument.")