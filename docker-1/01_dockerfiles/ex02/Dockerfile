### How to use: 
# docker build -t ft-rails:on-build .
# git clone https://bitbucket.org/railstutorial/sample_app_4th_ed.git sample_app_reference
# docker build .
# docker run -it --rm -p 3000:3000 <image id>

FROM ruby

RUN apt-get update && \
	apt-get install nodejs -y && \
	gem install rails && \
	mkdir -p /opt/app

ONBUILD WORKDIR /opt/app
ONBUILD ADD . /opt/app

ONBUILD EXPOSE 3000
ONBUILD RUN bundle install && rake db:migrate && rake db:seed
