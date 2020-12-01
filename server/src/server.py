from flask import Flask 
import cpp_logic
import time

app = Flask(__name__)

def wolanie():
	cpp_logic.performCalculations()

@app.route('/')
def main_site():
	print("dzialam1")
	wolanie()
	time.sleep(4)
	print("dzialam2")
	return 'Elo'

