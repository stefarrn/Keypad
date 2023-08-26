const { SerialPort } = require('serialport')

const PORT = "COM6"

const port = new SerialPort({
  path: PORT,
  baudRate: 115200
})

port.on('data', function (data) {
  console.log('Data:', data)
  process.exit()
})