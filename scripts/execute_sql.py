import logging as log
import psycopg2 as pg
import sys

def main():
	try:
		conn = pg.connect(host="localhost", database="flat_mate", user="flat_mate", password="flat_mate_pass")
	except Exception as e:
		log.error("Cannot connect to the db: " + str(e))
		exit()

	cur = conn.cursor()
	filename = sys.argv[1]

	with open(filename, "r") as f:
		query = f.read()
		try:
			cur.execute(query)
			conn.commit()
			log.info("Successfuly executed " + filename)

		except Exception as e:
			log.warning("Exception when executing statement: " + str(e))
			exit()

				
	cur.close()
	conn.close()
	

if __name__ == "__main__":
	log.basicConfig(level=log.INFO)

	if len(sys.argv) != 2:
		log.info("Usage: execute_sql.py filename")
		exit()

	main()
