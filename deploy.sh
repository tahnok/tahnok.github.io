bundle exec jekyll build
rsync -v -rz --checksum --delete public_html/ debian@oolong.tahnok.ca:/data/blog
