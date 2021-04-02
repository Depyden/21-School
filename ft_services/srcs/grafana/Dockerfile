FROM alpine

RUN apk update
RUN apk add openrc 
RUN apk add grafana --repository=http://dl-3.alpinelinux.org/alpine/edge/testing/

COPY ./srcs/start.sh /

COPY ./srcs/grafana.ini /usr/share/grafana/conf/custom.ini
COPY ./srcs/datasources.yaml /usr/share/grafana/conf/provisioning/datasources/influxdb.yaml
COPY ./srcs/dashboards.yaml /usr/share/grafana/conf/provisioning/dashboards/influxdb.yaml

RUN mkdir -p /var/lib/grafana_db/
COPY ./srcs/dashboard.json /var/lib/grafana_db/

RUN chmod 755 start.sh

EXPOSE 3000

CMD ["sh", "start.sh"]