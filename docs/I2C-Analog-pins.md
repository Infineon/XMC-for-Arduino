Arduino Uno R3 format dictates that A4 and A5 are also used for I2C operations, so when I2C is enabled analogue inputs A4 and A5 are **NOT** available.

On Arduino Uno R3 this is an alternate pin function, depending on which XMC-for-Arduino boards this could be an alternate pin function, or other case as described below.
<table>
 <tr>
  <td><b>Board</b></td>
  <td><b>Functionality</b></td>
  <td><b>Note</b></td>
 </tr>
 <tr>
  <td>XMC1100 Boot Kit</td>
  <td><b>NOT supported</b></td>
  <td>A4 + A5 are separate<br>A6 + A7 are alternate pin configurations to I2C</td>
 </tr>
 <tr>
  <td>XMC1300 Boot Kit</td>
  <td><b>NOT</b> same pin format<br> as Arduino Uno R3</td>
  <td>A10 + A11 are alternate pin configurations to I2C</td>
 </tr>
 <tr>
  <td>XMC1400 Arduino Kit</td>
  <td>Alternate pin function</td>
  <td>Matches Arduino Uno</td>
 </tr>
 <tr>
  <td>XMC4400 Platform 2Go</td>
  <td><b>External</b> hard wired pins</td>
  <td>For 3V3 boards set I2C pins to tristate or open drain to use<br>
      For 5V boards see Wiki board page on track cuts to enable A4 and A5 to work<br>
      Level shifter on the 5V board could interfere with tristate/open drain setting
 </td>
 </tr>
  <tr>
  <td>XMC4700 Relax Kit<br>(and variants)</td>
  <td><b>External</b> hard wired pins</td>
  <td>For 3V3 boards set I2C pins to tristate or open drain to use<br>
      For 5V boards see Wiki board page on track cuts to enable A4 and A5 to work<br>
      Level shifter on the 5V board could interfere with tristate/open drain setting
 </td>
 </tr>
</table>
