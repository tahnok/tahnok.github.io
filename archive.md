---
layout: page
title: Archive
permalink: /archive/
---

{% for post in site.posts %}
  <p>{{post.date | date: "%F"}}: <a href="{{ post.url }}">{{ post.title }}</a></p>
{% endfor %}
