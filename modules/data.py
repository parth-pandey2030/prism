# This file hold information for processing data such as:
# JSON (JavaScript Object Notation)
# YAML (YAML Ain't Markup Language)
# TOML (Tom's Obvious, Minimal Language)

import yaml
import toml
import json

def parse(data, type_of_data):
    if type_of_data == 'JSON': return json.loads(data) 
    elif type_of_data == 'YAML': return json.dumps(yaml.safe_load(data))
    elif type_of_data == 'TOML': return json.dumps(toml.loads(data))
    else: return 'UnknownTypeError: Unknown type of data'
    
# Tests:
# (JSON gotten from https://www.w3schools.com/python/python_json.asp)
# The commented lines below are the tests:
# json_test = parse('{ "name":"John", "age":30, "city":"New York"}', 'JSON')
# yaml_test_data = """
# key1: value1
# key2:
#   - item1
#   - item2
# key3:
#   nested_key: nested_value
# """
# yaml_test = parse(yaml_test_data, 'YAML')
# toml_test_data = """
# key1 = "value1"
# [key2]
# item1 = 1
# item2 = 2
# """
# toml_test = parse(toml_test_data, 'TOML')
# undef_test = parse('efWEF   WEF WE', 'WFRG')
# print(json_test)
# print(yaml_test)
# print(toml_test)