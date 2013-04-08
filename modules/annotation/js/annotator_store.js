(function ($) {
  Drupal.behaviors.annotatorStore = {
    attach: function (context, settings) {
      var loadSearch = (settings.annotator_store.toggle_search) ? 
        {'limit': 0,'uri': window.location.href} : false;
      var id = $('.node');

      Drupal.Annotator.annotator('addPlugin', 'Store', {
        prefix: settings.annotator_store.prefix,
        urls: settings.annotator_store.urls,
        showViewPermissionsCheckbox: settings.annotator_store.showViewPermissionsCheckbox,
        showEditPermissionsCheckbox: settings.annotator_store.showEditPermissionsCheckbox,
        annotationData: {
          'uri': window.location.href
        },
        loadFromSearch: loadSearch

      });
    }
  };
})(jQuery);