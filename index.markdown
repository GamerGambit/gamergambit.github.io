---
layout: default
---

### Latest Blog Posts
<div class="card-group">
  {% for post in site.posts limit:3 -%}
    {% include postcard.html %}
  {% else %}
  <div class="card">
    <div class="card-body">
        <p class="card-text">Looks like theres no posts yet.</p>
    </div>
  </div>
  {% endfor -%}
</div>
