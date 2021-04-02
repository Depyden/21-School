FROM alpine

RUN apk update

RUN apk add openrc

RUN apk add nginx supervisor

RUN apk add php7 php7-fpm php7-mbstring php7-session php7-json php7-mysqli php7-zlib php7-curl

RUN wget https://wordpress.org/latest.zip

RUN unzip latest.zip

RUN mv wordpress /www/

RUN rm latest.zip

COPY ./srcs/nginx.conf /etc/nginx/conf.d/default.conf
COPY ./srcs/supervisord.conf /etc/supervisord.conf
COPY ./srcs/wp-config.php /www/wp-config.php
COPY ./srcs/start.sh .
RUN chmod 777 start.sh

EXPOSE 5050

CMD ["sh", "start.sh"]
