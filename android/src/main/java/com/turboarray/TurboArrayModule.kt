package com.turboarray

import com.facebook.react.bridge.ReactApplicationContext
import com.facebook.react.module.annotations.ReactModule

@ReactModule(name = TurboArrayModule.NAME)
class TurboArrayModule(reactContext: ReactApplicationContext) :
  NativeTurboArraySpec(reactContext) {

  override fun getName(): String {
    return NAME
  }

  // Example method
  // See https://reactnative.dev/docs/native-modules-android
  override fun multiply(a: Double, b: Double): Double {
    return a * b
  }

  companion object {
    const val NAME = "TurboArray"
  }
}
