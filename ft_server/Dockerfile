FROM debian:buster

RUN apt-get update
RUN apt-get upgrade -y

RUN apt-get -y install nginx

RUN apt-get -y install mariadb-server

RUN apt-get -y install php7.3 php-mysql php-fpm php-cli php-mbstring

RUN apt-get -y install wget

COPY ./srcs/start.sh /var/
COPY ./srcs/mysql_setup.sql /var/
COPY ./srcs/wordpress-5.5.1.tar.gz /var/www/html/
COPY ./srcs/nginx.conf /etc/nginx/sites-available/localhost
COPY ./srcs/autoindex.sh /
RUN ln -s /etc/nginx/sites-available/localhost /etc/nginx/sites-enabled/localhost

WORKDIR /var/www/html/
RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.5/phpMyAdmin-4.9.5-english.tar.gz
RUN tar xf phpMyAdmin-4.9.5-english.tar.gz && rm -rf phpMyAdmin-4.9.5-english.tar.gz
RUN mv phpMyAdmin-4.9.5-english phpmyadmin
COPY ./srcs/config.inc.php phpmyadmin

RUN tar xf ./wordpress-5.5.1.tar.gz && rm -rf wordpress-5.5.1.tar.gz
RUN chmod 755 -R wordpress
COPY ./srcs/wp-config.php /var/www/html/wordpress

RUN service mysql start && mysql -u root mysql < /var/mysql_setup.sql 
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -subj '/C=RU/ST=21/L=Moscow/O=42/CN=lregenar' -keyout /etc/ssl/certs/localhost.key -out /etc/ssl/certs/localhost.crt
RUN chown -R www-data:www-data *
RUN chmod 755 -R *

CMD bash /var/start.sh

EXPOSE 80 443
