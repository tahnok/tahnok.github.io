---
layout: post
title: "Migrating to jekyll for blog style outpourings"
date: 2015-03-15 14:55:42 -0400
---

Recently, my (previous) blog hosting platform decided to axe their free tier and the price they were asking was too much for me. Plus, I'd be thinking for a long time about how it would be nice to do the hosting by myself. In addition to cutting my dependence on an external service, I'd get to learning more about ops-y things in the process.

My first attempt at this migration was with Octopress, which I'd dabled with a bit in the past. I quickly abandoned it though because it felt much too complicated. The default theme was split too many times, there were weird and (to me) unneeded layers of complexity.

Instead, I chose to use the platform Octopress is based on: Jekyll. It produces a nice clean site of interlinked and static HTML pages (which should be easy to host). It consumes posts or pages in either markdown or html, so I can write a post however I want. It has a simple template system and a theme that fits in my head so I can make it look like how I want without throwing something at the wall.

Important the old content was a bit tricky, but there's a nice plugin someone wrote to import an rss feed into jekyll that you can find [here](https://github.com/jekyll/jekyll-import). Just run `jekyll import rss --source http://blog.domain`

The only challenge I had was importing the images from the old site. I ended up writing a little script to grab a list of all the images, download them and then replace the src with a local reference. Here's the source for that

{% highlight ruby %}
require 'nokogiri'
require 'net/http'
require 'pry'

Dir.glob("octopress/source/_posts/*.html").each do |file_name|
  file = File.open(file_name, 'r+')
  post = file.read
  a,b,c = post.split("---")
  doc = Nokogiri::HTML::fragment(c)

  doc.css('img').each do |elm|
    img_elm = elm['src']
    uri = URI(img_elm)
    filename = "temp/" + File.basename(uri.to_s)
    if File.exists?(filename)
      puts "skipping " + filename
    else
      File.open(filename, 'wb') do |image|
        puts "downloading " + img_elm
        image.write(Net::HTTP.get(uri))
        sleep(2)
      end
    end

    elm['src'] = "../images/" + File.basename(uri.to_s)
  end
  file.rewind
  file.truncate(0)
  file.truncate(0)
  file.write([a,b,doc.to_html].join("---"))
  file.close
end
{% endhighlight %}

What's cool is that code up there is hosted on my site! I had been using gists before, but that's just one more thing that was outside of my control.

I considered a few alternatives. Wordpress is kind of the standard for this sort of thing, but it feels like there's a 0day every other week for it and I'm bad at patching. Plus I need a server capable of running a LAMP stack, whereas with something static (like this) I could host it on a 128 MB VPS that costs 15$ a year. Wait, [that's what I'm doing](http://buyvm.net/). Ghost looked interesting, but I don't know much about node or hosting a node site. I even thought about rolling my own, but  I tried that with [blag](https://github.com/tahnok/blag) and it didn't turn out quite the way I was hoping.

I will miss being able to write and publish a post anywhere I have an evernote account, but I think jekyll is good enough for now.

(ps do the comments work?)
