#!/usr/bin/env python3

import argparse
import os
import time

#______________________________________________________________________________
gray = '\x1b[90m'
green = '\x1b[32m'
magenta = '\x1b[35m'
red = '\x1b[31;1;5m'
cyan = '\x1b[36m'
default = '\x1b[0m'

NumOfRegion2 = 6
BeamDetectors = ['T1', 'BH2', 'BAC-unused', 'HTOF', 'T0', # 'SCH'
                 'BH2-6']
ScatDetectors = ['BEAM', 'SAC', 'KVC2', 'TOF-unused',
                 'KVC1', 'T2',
                 'BHT', 'BAC',
                 'M3D-unused', 'HTOF-Mp2',
                 'HTOF-Mp3']

#______________________________________________________________________________
def remove_escape(arg):
  arg = arg.replace(gray, '')
  arg = arg.replace(green, '')
  arg = arg.replace(magenta, '')
  arg = arg.replace(red, '')
  arg = arg.replace(cyan, '')
  arg = arg.replace(default, '')
  return arg

#______________________________________________________________________________
def bps(ctrl, coin):
  if ctrl == 0:
    return 'OFF'
  if coin == 0:
    return 'VETO'
  return 'ON'

#______________________________________________________________________________
def beam_bps(ctrl, coin):
  buf = ''
  for i, d in enumerate(BeamDetectors):
    b = bps((ctrl>>(len(BeamDetectors)-1-i))&1,
            (coin>>(len(BeamDetectors)-1-i))&1)
    if 'OFF' in b:
      continue
    elif 'VETO' in b:
      buf += cyan + '/'
    buf += d + default + 'x'
  if buf[-1:] == 'x':
    buf = buf[:-1]
  return buf

#______________________________________________________________________________
def scat_bps(ctrl, coin, beam):
  buf = ''
  for i, d in enumerate(ScatDetectors):
    b = bps((ctrl>>(len(ScatDetectors)-1-i))&1,
            (coin>>(len(ScatDetectors)-1-i))&1)
    if 'OFF' in b:
      continue
    elif 'VETO' in b:
      buf += cyan + '/'
    if i == 0:
      buf += beam + default + 'x'
    else:
      buf += d + default + 'x'
  if buf[-1:] == 'x':
    buf = buf[:-1]
  if len(buf) == 0:
    buf = red + 'N/A' + default
  return buf


#______________________________________________________________________________
def gate(val):
  if val == 0:
    return '-'
  elif val == 1:
    return 'on'
  elif val == 2:
    return 'off'
  elif val == 3:
    return 'on/off'
  else:
    return '-'

#______________________________________________________________________________
def onoff(val, char=False):
  on = '!' if char else 'ON '
  off = '.' if char else 'OFF'
  if val == 0:
    return f'{gray}{off}{default}'
  elif val == 1:
    return f'{green}{on}{default}'
  else:
    return ''

#______________________________________________________________________________
if __name__ == '__main__':
  # home = os.environ['HOME']
  parser = argparse.ArgumentParser()
  parser.add_argument('target', nargs='?',
                      default=f'/home/oper/share/hul-trig-ctrl/last.log',
                      help='target trigger_*****.log (default=last.log)')
  # parser.add_argument('-v', '--verbose', action='store_true',
  #                     help='increase output verbosity')
  parser.add_argument('-g', '--gate', action='store_false',
                      help='suppress gate information')
  parser.add_argument('-m', '--monitor', action='store_true',
                      help='show')
  parser.add_argument('-s', '--simple', action='store_true',
                      help='display trigger contents simply')
  parser.add_argument('-n', '--nocolor', action='store_true',
                      help='display without color')
  parsed, unparsed = parser.parse_known_args()
  if parsed.nocolor:
    gray = ''
    green = ''
    magenta = ''
    red = ''
    cyan = ''
    default = ''
  try:
    while True:
      try:
        param = dict()
        with open(parsed.target, 'r') as f:
          for line in f.readlines():
            line = line.split()
            if len(line) == 1 and line[0][0] != '#':
              param_file = line[0]
            if len(line) == 2 and line[0][0] != '#':
              param[line[0]] = int(line[1])
        os.system('clear')
        print(param_file, end='\n\n')
        ''' Region1 '''
        sel_tof = param['RGN1::SEL_TOF']
        tof_seg_01_08 = ''
        tof_seg_09_16 = ''
        tof_seg_17_24 = ''
        for i in range(8):
          tof_seg_01_08 += onoff((sel_tof >> (i +  0)) & 1, True)
          tof_seg_09_16 += onoff((sel_tof >> (i +  8)) & 1, True)
          tof_seg_17_24 += onoff((sel_tof >> (i + 16)) & 1, True)
        if sel_tof == 0:
          color = gray
        else:
          color = default
        if not parsed.simple:
          print(f'{color}TOF Seg# 01-08\t{tof_seg_01_08}\n' +
                f'{color}TOF Seg# 09-16\t{tof_seg_09_16}\n' +
                f'{color}TOF Seg# 17-24\t{tof_seg_17_24}\n{default}')
        # print(f'\t\tPS\t{"GATE" if parsed.gate else ""}')
        ''' Region3 '''
        sel_psor = param['RGN3::SEL_PSOR']
        label = ['(K,K)', '(K,pi)', 'BH2', 'BH2xTOFx/3D', 'LSOxGe', 'Ge coin']
        for i in range(NumOfRegion2):
          sel = onoff((sel_psor >> i) & 1)
          ps = param[f'RGN3::PS_R2{chr(65+i)}'] + 1
          g = gate(param[f'RGN3::GATE_R2{chr(65+i)}']) if parsed.gate else ''
          if 'OFF' in sel:
            color = gray
          else:
            color = default
          if not parsed.simple:
            print(f'TRIG-{chr(65+i)}      {sel}\t{color}1/{ps}\t{g}{default}')
          # print(f'{label[i]:12}{sel}\t{color}1/{ps}\t{g}{default}')
          # if 'OFF' in sel:
          #   continue
          ''' Region2 '''
          ctrl = param[f'RGN2{chr(65+i)}::BPS_CTRL_BEAM']
          coin = param[f'RGN2{chr(65+i)}::BPS_COIN_BEAM']
          beam = beam_bps(ctrl, coin)
          ctrl = param[f'RGN2{chr(65+i)}::BPS_CTRL_SCAT']
          coin = param[f'RGN2{chr(65+i)}::BPS_COIN_SCAT']
          scat = scat_bps(ctrl, coin, beam)
          if parsed.simple:
            print(f'TRIG-{chr(65+i)}\t' + remove_escape(scat))
          elif 'OFF' in sel:
            print(color + ' ' + remove_escape(scat) + default)
          else:
            print(' ' + scat + default)
        if parsed.simple:
          break
        print()
        ''' Region4 '''
        sel_clk = onoff(param['RGN4::SEL_EXTCLK'] |
                        param['RGN4::SEL_CLK10M'] |
                        param['RGN4::SEL_CLK1M'] |
                        param['RGN4::SEL_CLK100k'] |
                        param['RGN4::SEL_CLK10k'] |
                        param['RGN4::SEL_CLK1k'])
        g = gate(param['RGN4::GATE']) if parsed.gate else ''
        if 'OFF' in sel_clk:
          color = gray
        else:
          color = default
        print(f'Clock       {sel_clk}{color}\t-\t{g}{default}')
        sel_rsv2 = onoff(param['RGN4::SEL_RSV2'])
        if 'OFF' in sel_rsv2:
          color = gray
        else:
          color = default
        print(f'Rsv2        {sel_rsv2}{color}\t-\t{g}{default}',
              end='\x1b[200C' if not parsed.nocolor else '', flush=True)
        if parsed.monitor:
          time.sleep(1)
      except KeyError:
        print()
      if not parsed.monitor:
        break
  except KeyboardInterrupt:
    print()
  except FileNotFoundError as e:
    print(e)
