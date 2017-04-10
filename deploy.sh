bundle exec jekyll build
rsync -v -rz --checksum --delete public_html/ wes@blog.tahnok.me:/var/www/blog.tahnok.me
