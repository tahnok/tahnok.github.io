bundle exec jekyll build
rsync -v -rz --checksum --delete public_html/ wes@tahnok.me:/usr/share/nginx/blog/
