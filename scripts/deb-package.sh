#!/bin/bash

rm -f ../qtictactoe_*
debuild --no-tgz-check
dh clean
