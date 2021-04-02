FROM alpine

RUN apk update

RUN apk add openrc

RUN apk add nginx supervisor

RUN apk add php7 php7-fpm php7-mbstring php7-session php7-json php7-mysqli php7-zlib php7-curl

RUN mkdir -p /usr/share/webapps/

RUN wget http://files.directadmin.com/services/all/phpMyAdmin/phpMyAdmin-5.0.4-all-languages.tar.gz

RUN tar zxvf phpMyAdmin-5.0.4-all-languages.tar.gz
RUN rm phpMyAdmin-5.0.4-all-languages.tar.gz
RUN mv phpMyAdmin-5.0.4-all-languages /www/

COPY ./srcs/nginx.conf /etc/nginx/conf.d/default.conf
COPY ./srcs/supervisord.conf /etc/supervisord.conf
COPY ./srcs/config.inc.php /www/config.inc.php
COPY ./srcs/start.sh .

RUN chmod 755 start.sh

EXPOSE 5000

CMD ["sh", "start.sh"]
