import mysql.connector
from mysql.connector import Error
import pymysql.cursors

conn = pymysql.connect(host='93.89.225.103',port = 3306,user='fpnsmart_leo321',password='Jv818q9g',database='fpnsmart_weater',cursorclass=pymysql.cursors.DictCursor)
with conn:
    with conn.cursor() as cursor:
        # Create a new record
        sql = "INSERT INTO `ornek` (`email`, `password`) VALUES (%s, %s)"
        cursor.execute(sql, ('ksu_leo@gmail.com', '5456'))

    # connection is not autocommit by default. So you must commit to save
    # your changes.
    conn.commit()