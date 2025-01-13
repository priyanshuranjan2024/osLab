#!/bin/bash
# Display details of processes with parent ID 2

ps_output=$(ps -ef | awk '$3 == 2')  # Extract processes with PPID 2
if [[ -z "$ps_output" ]]; then
  echo "No process found with parent ID 2."
else
  echo "Processes with parent ID 2:"
  echo "$ps_output"
fi
