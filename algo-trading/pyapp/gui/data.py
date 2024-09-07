

import sqlalchemy

engine = sqlalchemy.create_engine('postgresql://qa:qa@localhost:5432/qa')
connection = engine.connect()
result = connection.execute("SELECT COUNT(*) FROM my_table")
count_result = result.scalar()
connection.close()