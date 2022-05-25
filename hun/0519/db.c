#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

static char *host = "localhost";
static char *user = "root";
static char *pass = "kcci";
static char *dbname = "test";
int main()
{
	MYSQL *conn;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;
	conn = mysql_init(NULL);

	if(!(mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)))
	{
		fprintf(stderr, "ERROR:%s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	printf("Connection Success\n\n");

	char temp[100];
	sprintf(temp, "select *from states");

	int res = mysql_query(conn, temp);
	if(!res){
	res_ptr = mysql_store_result(conn);
		if(res_ptr)
			{
			printf("Retreived %lu rows\n", (unsigned long)mysql_num_rows(res_ptr));
			while((sqlrow = mysql_fetch_row(res_ptr)))
				printf("%10s %10s %10s\n", sqlrow[0], sqlrow[1], sqlrow[2]);
			}
				//printf("insert %lu rows\n", (unsigned long) mysql_affected_rows(conn));
		}
	else
		fprintf(stderr, "select error %d: %s\n", mysql_errno(conn), mysql_error(conn));
	mysql_free_result(res_ptr);
	mysql_close(conn);
	return EXIT_SUCCESS;
}
