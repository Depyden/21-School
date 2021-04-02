FROM alpine 

RUN apk update
RUN	apk add nginx
RUN apk add openrc 
RUN apk add openssh
RUN apk add openssl
RUN apk add supervisor
RUN apk add tar
RUN apk add curl
RUN apk add gettext
RUN apk add vim

RUN	adduser -D 'lregenar'
RUN	echo "lregenar:lregenar" | chpasswd
RUN ssh-keygen -A
RUN mkdir -p /ssl/
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -subj '/C=RU/ST=Russia/L=Moscow/O=School21/CN=lregenar' -keyout /etc/ssl/localhost.key -out /etc/ssl/localhost.crt

COPY srcs/index.html /var/www/localhost/htdocs
COPY srcs/nginx.conf /etc/nginx/conf.d/default.conf
COPY srcs/ssbd_conf /etc/ssh/ssbd_conf
COPY srcs/supervisord.conf /etc/supervisord.conf
COPY srcs/start.sh /tmp/start.sh

RUN chmod +x /tmp/start.sh

EXPOSE 80 443 22

CMD ["sh", "-c", "/tmp/start.sh ; /usr/bin/supervisord -c /etc/supervisord.conf"]
