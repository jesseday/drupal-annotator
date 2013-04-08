(function ($) {
  Drupal.behaviors.annotator = {
    attach: function (context, settings) {

      var selector = (Drupal.settings.annotator_selector) ?
          Drupal.settings.annotator_selector : '.content';

      if(Drupal.settings.annotator_enabled_node_types) {
          var enabled = '';
          var count = Drupal.settings.annotator_enabled_node_types.length - 1;
          Drupal.settings.annotator_enabled_node_types.forEach(function(name, index) {
              enabled += name + ' ' + selector;
              enabled += (index < count) ? ', ' : '';
          });

          Drupal.Annotator = $(enabled).annotator();

      }
      else {
          selector = '.node ' + selector;
          Drupal.Annotator = $(selector).annotator();
      }

    }
  };
})(jQuery);