import serial
import time
import threading

# ANSI Color Codes for Terminal
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
CYAN = "\033[36m"
RESET = "\033[0m"

def read_serial(pico):
    """ Continuously reads and prints incoming data from the Pico. """
    while True:
        if pico.in_waiting > 0:
            line = pico.readline().decode('ascii', errors='replace').strip()
            if line:
                print(BLUE + "> " + CYAN + line + RESET)

def main():
    pico_port = 'COM7'  # Change this to match your board
    baud_rate = 115200

    try:
        with serial.Serial(pico_port, baud_rate, timeout=1) as pico:
            print("---------------------------------------------")
            print("|" + GREEN + "                     BRG                   " + RESET + "|")
            print("|" + GREEN + "              Chip Tester v1.0             " + RESET + "|")
            print("|" + GREEN + "               Parker Schless              " + RESET + "|")
            print("|" + GREEN + "                    2025                   " + RESET + "|") 
            print("---------------------------------------------")
            port_number = ''.join(filter(str.isdigit, pico_port))
            formatted_port = f"0{port_number}" if len(port_number) == 1 else port_number
            print("|" + GREEN + f"     Connected to Tester Board on COM{formatted_port}    " + RESET + "|")
            print("---------------------------------------------")

            # Start real-time reading in a separate thread
            serial_thread = threading.Thread(target=read_serial, args=(pico,), daemon=True)
            serial_thread.start()

            while True:
                # Get user input and send to Pico
                data_to_send = input()
                if data_to_send.lower() == "exit":
                    print(YELLOW + "Exiting program..." + RESET)
                    break
            
                pico.write(data_to_send.encode('ascii'))  # Send to Pico

    except serial.SerialException as e:
        print(RED + f"Error: {e}" + RESET)

if __name__ == "__main__":
    main()