from flask import Flask 
import cpp_logic
import time

app = Flask(__name__)

@app.route('/')
def main_site():
	cpp_logic.performCalculations(10000000)
	return 'Server is working!'

