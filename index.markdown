---
layout: default
---

### Latest Blog Posts
<div class="card-group">
  {% for post in site.posts reversed limit:3 -%}
    {% include postcard.html %}
  {% endfor -%}
</div>
