# To run: docker run -it --rm -p 10011:10011 -p 30033:30033 -p 9987:9987/udp <image id>
FROM debian

ENV TSV=3.0.13.8

RUN apt-get update && apt-get upgrade -y && apt-get install wget bzip2 -y
RUN mkdir /home/teamspeak && cd /home/teamspeak && \
	wget http://dl.4players.de/ts/releases/${TSV}/teamspeak3-server_linux_amd64-${TSV}.tar.bz2 && \
	tar -jxf teamspeak3-server_linux_amd64-${TSV}.tar.bz2 && \
	rm teamspeak3-server_linux_amd64-${TSV}.tar.bz2

EXPOSE 9987/udp
EXPOSE 30033
EXPOSE 10011
ENTRYPOINT ["/home/teamspeak/teamspeak3-server_linux_amd64/ts3server_minimal_runscript.sh"]
