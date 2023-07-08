---
layout: default
---

### Latest Blog Posts
<div class="row row-cols-1 row-cols-md-3 g-4">
  {% for post in site.posts limit:3 -%}
    {% include postcard.html %}
  {% else %}
  <div class="col">
    <div class="card">
      <div class="card-body">
          <p class="card-text">Looks like theres no posts yet.</p>
      </div>
    </div>
  </div>
  {% endfor -%}
</div>
