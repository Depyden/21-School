FROM alpine

RUN apk update

RUN apk add openrc 

RUN apk add mysql mysql-client

RUN mkdir "/run/mysq_ld"

RUN chown -R mysql /run/mysq_ld

COPY ./srcs/mysql_conf.sql /srcs/lregenar.sql /srcs/start.sh ./

COPY ./srcs/my.cnf /etc/my.cnf

EXPOSE 3306

RUN chmod 755 start.sh

CMD ["sh", "start.sh"]