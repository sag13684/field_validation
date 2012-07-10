<?php

namespace Drupal\field_validation\Plugins\Type;

use Drupal\Component\Plugin\PluginType;
use Drupal\Core\Plugin\Discovery\HookDiscovery;
use Drupal\Component\Plugin\Discovery\DerivativeDiscoveryDecorator;
use Drupal\Component\Plugin\Factory\DefaultFactory;

class Validator extends PluginType {
  public function __construct() {
    $this->discovery = new DerivativeDiscoveryDecorator(new HookDiscovery('validator_info'));
    $this->factory = new DefaultFactory($this);
  }
}
