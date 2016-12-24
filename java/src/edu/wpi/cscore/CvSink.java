/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2016. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.cscore;

import org.opencv.core.Mat;

/// A sink for user code to accept video frames as OpenCV images.
public class CvSink extends VideoSink {
  /// Create a sink for accepting OpenCV images.
  /// WaitForFrame() must be called on the created sink to get each new
  /// image.
  /// @param name Source name (arbitrary unique identifier)
  public CvSink(String name) {
    super(CameraServerJNI.createCvSink(name));
  }

  /// Create a sink for accepting OpenCV images in a separate thread.
  /// A thread will be created that calls WaitForFrame() and calls the
  /// processFrame() callback each time a new frame arrives.
  /// @param name Source name (arbitrary unique identifier)
  /// @param processFrame Frame processing function; will be called with a
  ///        time=0 if an error occurred.  processFrame should call GetImage()
  ///        or GetError() as needed, but should not call (except in very
  ///        unusual circumstances) WaitForImage().
  //public CvSink(llvm::StringRef name,
  //       std::function<void(uint64_t time)> processFrame) {
  //  super(CameraServerJNI.createCvSinkCallback(name, processFrame));
  //}

  /// Set sink description.
  /// @param description Description
  public void setDescription(String description) {
    CameraServerJNI.setSinkDescription(m_handle, description);
  }

  /// Wait for the next frame and get the image.
  /// The provided image will have three 3-bit channels stored in BGR order.
  /// @return Frame time, or 0 on error (call GetError() to obtain the error
  ///         message);
  public long grabFrame(Mat image) {
    return CameraServerJNI.grabSinkFrame(m_handle, image.nativeObj);
  }

  /// Get error string.  Call this if WaitForFrame() returns 0 to determine
  /// what the error is.
  public String getError() {
    return CameraServerJNI.getSinkError(m_handle);
  }

  /// Enable or disable getting new frames.
  /// Disabling will cause processFrame (for callback-based CvSinks) to not
  /// be called and WaitForFrame() to not return.  This can be used to save
  /// processor resources when frames are not needed.
  public void setEnabled(boolean enabled) {
    CameraServerJNI.setSinkEnabled(m_handle, enabled);
  }
}
