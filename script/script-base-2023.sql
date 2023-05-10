create table localidad(cod_postal int primary key, 
					   nombre varchar(60));
					   
create table tipo_actividad(codigo serial primary key, 
					   nombre varchar(90));

create table importe_actividad(codigo serial primary key,					   
					   cod_tipo_act int,
					   anio int, 
					   mes int, 
					   importe float
					   );
alter table importe_actividad add constraint fk_importe_actividad_tipo_actividad foreign key (cod_tipo_act)references tipo_actividad(codigo);
					   
create table socio(nro_socio serial primary key,
				   dni int, 
				   nombres varchar(80), 
				   apellido varchar(90), 
				   domicilio varchar(120), 
				   telefono varchar(20),
				   cod_postal int,  
				   observaciones varchar(250), 
				   activo boolean, 
				   moroso boolean );

alter table socio add constraint fk_socio_localidad foreign key(cod_postal) references localidad(cod_postal);

create table profesor(legajo serial primary key,
				   dni int not null, 
				   nombres varchar(80), 
				   apellido varchar(90), 
				   domicilio varchar(120), 
				   telefono varchar(20)
				   );

create table actividad(codigo serial primary key,					   
					   cod_tipo_act int,
					   legajo_profe int, 
					   fecha_desde date,
					   fecha_fin date
					   );
alter table actividad add constraint fk_actividad_tipo_actividad foreign key(cod_tipo_act) references tipo_actividad(codigo);
alter table actividad add constraint fk_actividad_prodesor foreign key(legajo_profe) references profesor(legajo);

create table actividad_socio(codigo serial primary key,
					   nro_socio int,
					   cod_act int, -- referencia a la actividad
					   fecha_inicio date not null, 
					   fecha_fin date
					   );

alter table actividad_socio add constraint fk_actividad_socio_actividad foreign key (cod_act) references actividad(codigo);
alter table actividad_socio add constraint fk_actividad_socio_socio foreign key (nro_socio) references socio(nro_socio);

create table cuotas(codigo serial primary key,
				    cod_act_socio int,
					anio int,
					mes int,
					estado varchar(1),
					importe float,
					fecha_venc date,
					fecha_pago date
					);
alter table cuotas add constraint fk_cuotas_actividad_socio foreign key (cod_act_socio) references actividad_socio(codigo);

create table horarios(codigo serial primary key, dia int,cod_act int,hora_desde timestamp,hora_hasta timestamp, lugar varchar(90));
alter table horarios add constraint fk_horarios_actividad foreign key (cod_act) references actividad(codigo);
